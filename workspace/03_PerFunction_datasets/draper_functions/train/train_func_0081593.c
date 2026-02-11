lirc_ctor(const fn_call&  fn)
{
    as_object* obj = ensure<ValidThis>(fn);

    obj->setRelay(new LircRelay());

    return as_value();
}
