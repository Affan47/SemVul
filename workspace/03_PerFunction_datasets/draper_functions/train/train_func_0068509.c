bus_recipient_unref (BusRecipient *recipient)
{
    recipient->refcount --;
    if (recipient->refcount == 0) {
        bus_recipient_free (recipient);
        return TRUE;
    }
    return FALSE;
}
