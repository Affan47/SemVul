position_set_black_king (Position *pos, Square square)
{
	g_return_if_fail (pos != NULL);
	g_return_if_fail (IS_POSITION (pos));

	pos->priv->bk_square = square;
}
