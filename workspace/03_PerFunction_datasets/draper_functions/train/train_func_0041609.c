event_handle_prompt(ObPrompt *p, XEvent *e)
{
    switch (e->type) {
    case ButtonPress:
    case ButtonRelease:
    case MotionNotify:
        return prompt_mouse_event(p, e);
        break;
    case KeyPress:
        return prompt_key_event(p, e);
        break;
    }
    return FALSE;
}
