decode(DecodeBuffer & decodeBuffer)
{
    unsigned int result = root_->decode(decodeBuffer);

    if (result >= numTokens_)
        decodeBuffer.decodeValue(result, 16, 8);
    return result;
}
