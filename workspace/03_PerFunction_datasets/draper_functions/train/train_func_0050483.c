handleSoundTalk(Person* p, const std::string& speech)
{
    assert(p);

    if (m_members.count(p->getAccount()) == 0) {
        error() << "room " << m_roomId << " got sound(talk) from non-member account";
        return;
    }

    Speech.emit(this, p, speech);
}
