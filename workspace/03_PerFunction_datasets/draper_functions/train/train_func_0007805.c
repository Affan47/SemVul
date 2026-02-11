localeToWchar(char *str){
	  wchar_t * ptr;
	  size_t s;


	  s = mbstowcs(NULL, str, 0);


	  if(s == -1){
		  puts("Error: could not convert to wchar");
		  exit(1);
	  }

	  if((ptr = (wchar_t *)malloc((s + 1) * sizeof(wchar_t))) == NULL){
          puts("Error: Could not allocate memory");
		  exit(1);
	  }

	  mbstowcs(ptr, str, s);


	  ptr[s] = L'\0';

	  return(ptr);
}
