mpc_re_escape_char(char c) {
  switch (c) {
    case 'a': return mpc_char('\a');
    case 'f': return mpc_char('\f');
    case 'n': return mpc_char('\n');
    case 'r': return mpc_char('\r');
    case 't': return mpc_char('\t');
    case 'v': return mpc_char('\v');
    case 'b': return mpc_and(2, mpcf_snd, mpc_boundary(), mpc_lift(mpcf_ctor_str), free);
    case 'B': return mpc_not_lift(mpc_boundary(), free, mpcf_ctor_str);
    case 'A': return mpc_and(2, mpcf_snd, mpc_soi(), mpc_lift(mpcf_ctor_str), free);
    case 'Z': return mpc_and(2, mpcf_snd, mpc_eoi(), mpc_lift(mpcf_ctor_str), free);
    case 'd': return mpc_digit();
    case 'D': return mpc_not_lift(mpc_digit(), free, mpcf_ctor_str);
    case 's': return mpc_whitespace();
    case 'S': return mpc_not_lift(mpc_whitespace(), free, mpcf_ctor_str);
    case 'w': return mpc_alphanum();
    case 'W': return mpc_not_lift(mpc_alphanum(), free, mpcf_ctor_str);
    default: return NULL;
  }
}
