is_destructible( char brick )
{
    if ( (brick >= 'a' && brick <= 'k') ||
         (brick >= 'x' && brick <= 'z') ||
          brick == 'v' ||
          brick == '*' ||
          brick == '!' )
        return 1;
    return 0;
}
