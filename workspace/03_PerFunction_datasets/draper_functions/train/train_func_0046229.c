ibus_unikey_engine_reset(IBusEngine* engine)
{
    unikey = (IBusUnikeyEngine*)engine;

    UnikeyResetBuf();
    if (unikey->preeditstr->length() > 0)
    {
        ibus_engine_hide_preedit_text(engine);
        ibus_unikey_engine_commit_string(engine, unikey->preeditstr->c_str());
        unikey->preeditstr->clear();


    }

    parent_class->reset(engine);
}
