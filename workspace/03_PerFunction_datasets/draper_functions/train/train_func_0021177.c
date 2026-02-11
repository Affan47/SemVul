indent(struct buffer* b, size_t amount)
{
    size_t spaces = amount * 4;

    char temp[spaces + 1];

    for(size_t i = 0; i < spaces; ++i)
        temp[i] = ' ';
    temp[spaces] = '\0';

    bprintf(b, "%s", temp);
}
