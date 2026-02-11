enable_repl(
    const DEFBUF *  defp,
    int         done
)


{
    if (defp == NULL)
        return;
    replacing[ rescan_level - 1].def = NULL;
    if (done && rescan_level)
        rescan_level--;
}
