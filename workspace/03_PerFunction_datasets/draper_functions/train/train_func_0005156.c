do_undo()
{
	if ( input_undo.canUndo() )
		cursor_position = input_undo.doUndo( text );
}
