finalizeReply()
{
    const SerializationInfo* s = _deserializer->si()->findMember("error");

    if (s && !s->isNull())
    {
        log_debug("remote error detected category=" << s->category() << " type=" << s->typeName());

        std::string msg;
        if (s->category() == SerializationInfo::Object)
        {
            int rc = 0;
            s->getMember("code", rc);
            s->getMember("message", msg);
            throw RemoteException(msg, rc);
        }
        else
        {
            s->getValue(msg);
            if (msg.empty())
                msg = "remote exception";

            throw RemoteException(msg);
        }
    }

    _composer->fixup(
        _deserializer->si()->getMember("result"));
}

}
}
