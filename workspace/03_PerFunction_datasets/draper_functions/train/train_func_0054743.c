Ascender() const
{
    return ftSize == 0 ? 0.0f : static_cast<float>(ftSize->metrics.ascender) / 64.0f;
}
