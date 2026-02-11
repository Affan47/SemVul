CmdTikzPicture(int code)
{
    char *picture = NULL;
    char post[] = "\\end{tikzpicture}";

    if (!(code & ON)) {
        diagnostics(4, "exiting CmdTikzPicture");
        return;
    } else
        diagnostics(4, "entering CmdTikzPicture");

    picture = getTexUntil(post, 0);

    PrepareDisplayedBitmap("picture");
    if (g_figure_comment_converted) {
      WriteLatexAsBitmapOrEPS("\\begin{tikzpicture}", picture, post, EPS);
    } else {
      WriteLatexAsBitmapOrEPS("\\begin{tikzpicture}", picture, post, BITMAP);
    }
    FinishDisplayedBitmap();

    ConvertString(post);
    safe_free(picture);
}
