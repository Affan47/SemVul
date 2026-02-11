removeComma()
{
    if (buf->offset >= 2 &&
        buf->data[buf->offset - 2] == ',' &&
        (buf->data[buf->offset - 1] == '\n' || buf->data[buf->offset - 1] == ' '))
        buf->offset -= 2;
}
