vtterminalinfo(int termcap_wins)
{
    return((term.t_terminalinfo) ? (*term.t_terminalinfo)(termcap_wins)
				 : (Pmaster ? 0 : TRUE));
}
