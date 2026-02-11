gl_replace_prompt(GetLine *gl, const char *prompt)
{
  if(gl) {
    sigset_t oldset;


    gl_mask_signals(gl, &oldset);


    _gl_replace_prompt(gl, prompt);


    gl_unmask_signals(gl, &oldset);
  };
}
