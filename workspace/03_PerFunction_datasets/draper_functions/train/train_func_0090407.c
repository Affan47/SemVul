append_char_to_fragment(int c)
#else
append_char_to_fragment(c)
int c;
#endif
{
    if (pos_fragment < (MAX_STMT - 1))
	stmt_fragment[pos_fragment++] = c;
}
