commaize(s)
char *s;
{ int n,k,groups,j;

  k = strlen(s);

  while ( k > 0 )
  {

    for ( n = k; n > 0 ; n-- )
      if ( isdigit(s[n]) ) break;
    if ( !isdigit(s[n]) ) return;

    for ( k = n-1 ; k > 0 ; k-- )
      if ( !isdigit(s[k]) ) break;
    groups = (n-k-1)/3;
    for ( j = k+1 ; j < n ; j++ )
    { s[j-groups] = s[j];
      if ( ((n-j+groups) % 4) == 0  )
      { groups--;
        s[j-groups] = ',';
      }
    }
  }
}
