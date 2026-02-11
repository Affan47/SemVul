get_definition()
{
	definition *defp;
	token tok;

	defp = ALLOC(definition);
	get_token(&tok);
	switch (tok.kind) {
	case TOK_STRUCT:
		def_struct(defp);
		break;
	case TOK_UNION:
		def_union(defp);
		break;
	case TOK_TYPEDEF:
		def_typedef(defp);
		break;
	case TOK_ENUM:
		def_enum(defp);
		break;
	case TOK_PROGRAM:
		def_program(defp);
		break;
	case TOK_CONST:
		def_const(defp);
		break;
	case TOK_EOF:
		return (NULL);
		break;
	default:
		error("definition keyword expected");
	}
	scan(TOK_SEMICOLON, &tok);
	isdefined(defp);
	return (defp);
}
