blockExit(bool mustNotThrow)
{   int result = BEnone;
    if (condition->canThrow(mustNotThrow))
        result |= BEthrow;

    if (body)
    {   result |= body->blockExit(mustNotThrow);
        if (result & BEbreak)
        {   result |= BEfallthru;
            result &= ~BEbreak;
        }
    }
    else
        result |= BEfallthru;

    return result;
}
