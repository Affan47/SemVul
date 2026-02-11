fits_clean_url(char *inURL,
		   char *outURL,
		   int  *status)


{
  grp_stack* mystack;
  char* tmp;

  if(*status) return *status;

  mystack = new_grp_stack();
  *outURL = 0;

  do {

    tmp = strstr(inURL, "://");
    if(tmp) {

      tmp = strchr(tmp + 3, '/');
      if(tmp) {


        size_t string_size = (size_t) (tmp - inURL);
        strncpy(outURL, inURL, string_size);
        outURL[string_size] = 0;


        inURL = tmp;
      } else {


        strcpy(outURL, inURL);
        continue;
      }
    }


    if('/' == *inURL) strcat(outURL, "/");


    tmp = strtok(inURL, "/");
    while(tmp) {
      if(!strcmp(tmp, "..")) {


        if(0 < mystack->stack_size) pop_grp_stack(mystack);
        else if('/' != *inURL) push_grp_stack(mystack, tmp);
      } else {

        if(strcmp(tmp, ".")) push_grp_stack(mystack, tmp);
      }
      tmp = strtok(NULL, "/");
    }


    while(0 < mystack->stack_size) {
      tmp = shift_grp_stack(mystack);
      strcat(outURL, tmp);
      strcat(outURL, "/");
    }
    outURL[strlen(outURL) - 1] = 0;
  } while(0);
  delete_grp_stack(&mystack);
  return *status;
}
