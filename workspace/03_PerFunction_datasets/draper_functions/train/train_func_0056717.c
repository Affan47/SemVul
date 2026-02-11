marshal_test(node *state,node *self,node *obj,node *block,node *parameters)
{
  node *base_class = get_base_class(state);
  node *value = create_class_instance(base_class);
  set_obj_string(value,"name","marshal.test");
  add_garbage(state,value);
  node *real_value = get_value(value);
  printf("marshalling test\n");

  void *lib = dlopen("libc.so.6",RTLD_LAZY);
  if(lib==NULL)
  {
    printf("library not found\n");
  }
  else
  {
    printf("checking for printf call\n");
    void *sym = dlsym(lib,"printf");
    if(sym==NULL)
    {
      printf("no printf function found\n");
    }
    else
    {
      printf("trying printf call\n");
      func init = (func)sym;

      char *format = "printf[%s]\n";
      char *hello = "hello world";


      long ret = 0;

      __asm__ __volatile__(
        "movq %2,%%rdi\n\t"
        "movq %1,%%rsi\n\t"
        "movl $0,%%eax\n\t"
        "call %3\n\t"
        "movq %0,%%rax\n\t"
        : "=r" (ret)
        : "r" (hello),"r" (format), "r" (sym)
        :
      );
      printf("call finished\n");
      fflush(stdout);


    }
    dlclose(lib);
  }

  return(value);
}
