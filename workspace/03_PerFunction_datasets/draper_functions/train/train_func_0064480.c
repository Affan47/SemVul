ft_cardgetr(card)
	FITSCard	card;
{
        int	i;
        char	*s = ft_cardget(card);


	for(i=strlen(s)-1; i>=0; i--){
	  if( s[i] == 'D' ){
	    s[i] = 'E';
	    break;
	  }
	}
	return strtod(s, NULL);
}
