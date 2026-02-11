message_guid_import(struct message_guid *guid,
					 const unsigned char *buf)
{
    static struct message_guid tmp;

    if (!guid) guid = &tmp;

    guid->status = GUID_UNKNOWN;
    memcpy(guid->value, buf, MESSAGE_GUID_SIZE);

    return(guid);
}
