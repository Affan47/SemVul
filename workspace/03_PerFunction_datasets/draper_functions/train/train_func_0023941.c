parserLookAHeadChar(JsonParser *parser, char ch)
{
    int parseStringLen = strlen(parser->parseString);
    while(parser->currPosition < parseStringLen
          && parser->parseString[parser->currPosition] != ch)
    {
        parser->currPosition++;
    }
}
