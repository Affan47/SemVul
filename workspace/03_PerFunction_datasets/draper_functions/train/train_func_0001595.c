str() const
{
	char ss[6];

	snprintf(ss, sizeof(ss), "%s%s%c",
			square_str[from()],
			square_str[to()],
			(flags() & MOVE_PROMOTION) ?
					tolower(piece_char[promote_to()])
					: '\0' );

	return std::string(ss);
}
