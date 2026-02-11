line_number_of_character_at_offset(size_t idx) const
{
    if (! current_tokenizer)
        return -1;

    int result = current_tokenizer->line_number_of_character_at_offset(idx);

    return result;
}
