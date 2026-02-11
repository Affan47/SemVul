Read(trpgReadBuffer &buf)
{
    Reset();

    trpgr_Parser parse;
    textStyleCB textStyleCb;

    textStyleCb.style = this;
    parse.AddCallback(TRPG_TEXT_STYLE_BASIC,&textStyleCb,false);
    parse.Parse(buf);

    return isValid();
}
