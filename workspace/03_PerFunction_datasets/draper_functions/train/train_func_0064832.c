setTextShadow(ShadowData* val, bool add)
{
    StyleCSS3InheritedData* css3Data = css3InheritedData.access();
    if (!add) {
        delete css3Data->textShadow;
        css3Data->textShadow = val;
        return;
    }

    ShadowData* last = css3Data->textShadow;
    while (last->next) last = last->next;
    last->next = val;
}
