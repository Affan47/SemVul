blockExit(bool mustNotThrow)
{
    return handler ? handler->blockExit(mustNotThrow) : BEfallthru;
}
