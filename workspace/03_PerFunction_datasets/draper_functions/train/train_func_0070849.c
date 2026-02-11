plist_get_type_and_value(plist_t node, plist_type * type, void *value, uint64_t * length)
{
    plist_data_t data = NULL;

    if (!node)
        return;

    data = plist_get_data(node);

    *type = data->type;
    *length = data->length;

    switch (*type)
    {
    case PLIST_BOOLEAN:
        *((char *) value) = data->boolval;
        break;
    case PLIST_UINT:
    case PLIST_UID:
        *((uint64_t *) value) = data->intval;
        break;
    case PLIST_REAL:
        *((double *) value) = data->realval;
        break;
    case PLIST_KEY:
    case PLIST_STRING:
        *((char **) value) = strdup(data->strval);
        break;
    case PLIST_DATA:
        *((uint8_t **) value) = (uint8_t *) malloc(*length * sizeof(uint8_t));
        memcpy(*((uint8_t **) value), data->buff, *length * sizeof(uint8_t));
        break;
    case PLIST_DATE:

        ((struct timeval*) value)->tv_sec = data->timeval.tv_sec;
        ((struct timeval*) value)->tv_usec = data->timeval.tv_usec;
        break;
    case PLIST_ARRAY:
    case PLIST_DICT:
    default:
        break;
    }
}
