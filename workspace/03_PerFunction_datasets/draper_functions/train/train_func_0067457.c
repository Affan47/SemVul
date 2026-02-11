parseKeepAliveLine(char *line)
{
    char *value = next_field(&line);
    if (!strcmp(value, "on"))
        _output->setDoKeepalive(true);
    else if (!strcmp(value, "off"))
        _output->setDoKeepalive(false);
    else
        _output->setError(RESPONSE_CODE_INVALID_HEADER,
                "Invalid value for KeepAlive: must be 'on' or 'off'");
}
