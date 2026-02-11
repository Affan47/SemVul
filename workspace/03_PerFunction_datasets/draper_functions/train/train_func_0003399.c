linkFile(Entry *ce)
{
    if (ce->written && *ce->value)
        doLinkFile(ce->value);
}
