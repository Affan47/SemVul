push_hook_stack(EB_Hook_Code code)
{
	if(hook_level >= 255) {

		return;
	}
	hook_level ++;
	hook_stack[hook_level] = code;
}
