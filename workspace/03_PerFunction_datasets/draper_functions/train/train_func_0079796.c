hash_str2us(std::string s) {


  int result=0;
  int a=63689;
  int b=378551;


  if(s.length()<1)return -1;

  unsigned int i=0;
  for(i=0; i<s.length(); i++) {
    result=result*a+s[i];
    a *= b;
  }

  return ((unsigned short)(result) & 0x7FFFFFFF);
}
