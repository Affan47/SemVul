canPasteMimeSource(const QMimeData* data)
{
    return data->hasText() || !extractFormats(data).isEmpty();
}
