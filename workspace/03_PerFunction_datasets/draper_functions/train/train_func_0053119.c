scroll_state(int func)
{
    struct scrollstack {
	SCRLCTRL_S	    s;
	struct scrollstack *prev;
    } *s;
    static struct scrollstack *stack = NULL;

    switch(func){
      case SS_CUR:
	break;
      case SS_NEW:
	s = (struct scrollstack *)fs_get(sizeof(struct scrollstack));
	memset((void *)s, 0, sizeof(struct scrollstack));
	s->prev = stack;
	stack  = s;
	break;
      case SS_FREE:
	if(stack){
	    s = stack->prev;
	    fs_give((void **)&stack);
	    stack = s;
	}
	break;
      default:
	break;
    }

    return(stack ? &stack->s : NULL);
}
