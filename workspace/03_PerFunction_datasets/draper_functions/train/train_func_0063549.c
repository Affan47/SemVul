get_code(mixer *this)
{


  if (!this->code) {
    int i;
    char *cp;
    this->code = (char **)malloc(sizeof(char *) * 3);

    this->code[0] = (char *)malloc(sizeof(char) * (this->length * 40 + 50));
    cp = this->code[0];
    for(i = 0; i < this->length;i++)
      cp += sprintf(cp,"if($n_mute%d > 0)\n\t $n_amp%d = 0;\n",i,i);

    this->code[1] = (char *)malloc(sizeof(char) * (this->length * 40 + 50));
    cp = this->code[1];
    cp += sprintf(cp, "$o = ");
    for (i=0; i < this->length; i++) {
      cp += sprintf(cp, "($i%d * $n_amp%d / MIX_MAX_AMP)%s",
		    i, i, (i == this->length - 1) ? "" : " + ");
    }
    sprintf(cp, ";");
    this->code[2] = NULL;
  }


  return this->code;
}
