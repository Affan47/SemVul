PrintTempRecord(void)
{
    RfmTemp  temp;
    char    *buf;

    BUFFER_CLEAR(buf);

    for (temp = RFM_ModuleCurrent->temp_list;
         temp != NULL;
         temp = temp->next) {
        buf += sprintf(buf, "   ");
        buf = PrintRefAttr(buf, temp->ref_type);
        buf += sprintf(buf, " T%d;", temp->entry);
        NEW_LINE(buf);
    }
}
