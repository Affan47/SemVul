onkeydown(GtkWidget *widget, GdkEventKey *event, void *data)
{
    int key = event->keyval;

    if (event->state & GDK_CONTROL_MASK)
    {

        switch(key)
        {
            case GDK_a: case GDK_A: gli_input_handle_key(keycode_Home); break;
            case GDK_c: case GDK_C: winclipsend(CLIPBOARD); break;
            case GDK_e: case GDK_E: gli_input_handle_key(keycode_End); break;
            case GDK_u: case GDK_U: gli_input_handle_key(keycode_Escape); break;
            case GDK_v: case GDK_V: winclipreceive(CLIPBOARD); break;
            case GDK_x: case GDK_X: winclipsend(CLIPBOARD); break;
        }

        return;
    }

    if (!gtk_im_context_filter_keypress(imcontext, event))
    {

        switch (key)
        {
            case GDK_Return: gli_input_handle_key(keycode_Return); break;
            case GDK_BackSpace: gli_input_handle_key(keycode_Delete); break;
            case GDK_Delete: gli_input_handle_key(keycode_Erase); break;
            case GDK_Tab: gli_input_handle_key(keycode_Tab); break;
            case GDK_Prior: gli_input_handle_key(keycode_PageUp); break;
            case GDK_Next: gli_input_handle_key(keycode_PageDown); break;
            case GDK_Home: gli_input_handle_key(keycode_Home); break;
            case GDK_End: gli_input_handle_key(keycode_End); break;
            case GDK_Left: gli_input_handle_key(keycode_Left); break;
            case GDK_Right: gli_input_handle_key(keycode_Right); break;
            case GDK_Up: gli_input_handle_key(keycode_Up); break;
            case GDK_Down: gli_input_handle_key(keycode_Down); break;
            case GDK_Escape: gli_input_handle_key(keycode_Escape); break;
            case GDK_F1: gli_input_handle_key(keycode_Func1); break;
            case GDK_F2: gli_input_handle_key(keycode_Func2); break;
            case GDK_F3: gli_input_handle_key(keycode_Func3); break;
            case GDK_F4: gli_input_handle_key(keycode_Func4); break;
            case GDK_F5: gli_input_handle_key(keycode_Func5); break;
            case GDK_F6: gli_input_handle_key(keycode_Func6); break;
            case GDK_F7: gli_input_handle_key(keycode_Func7); break;
            case GDK_F8: gli_input_handle_key(keycode_Func8); break;
            case GDK_F9: gli_input_handle_key(keycode_Func9); break;
            case GDK_F10: gli_input_handle_key(keycode_Func10); break;
            case GDK_F11: gli_input_handle_key(keycode_Func11); break;
            case GDK_F12: gli_input_handle_key(keycode_Func12); break;
            default:
                if (key >= 32 && key <= 255)
                    gli_input_handle_key(key);
        }

    }
}
