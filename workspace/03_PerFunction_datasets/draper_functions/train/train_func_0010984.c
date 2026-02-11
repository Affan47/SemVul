macroModeClose()
{
	if (!inMacroMode())
		return false;
	InsetMathUnknown * p = activeMacro();
	p->finalize();
	MathData selection(buffer());
	asArray(p->selection(), selection);
	docstring const s = p->name();
	--pos();
	cell().erase(pos());


	if (s == "\\")
		return false;


	screenUpdateFlags(Update::Force);

	docstring const name = s.substr(1);
	InsetMathNest * const in = inset().asInsetMath()->asNestInset();
	if (in && in->interpretString(*this, s))
		return true;
	MathAtom atom = buffer()->getMacro(name, *this, false) ?
		MathAtom(new MathMacro(buffer(), name)) : createInsetMath(name, buffer());


	bool macroArg = false;
	MathMacro * atomAsMacro = atom.nucleus()->asMacro();
	if (atomAsMacro) {


		MacroData const * data = buffer()->getMacro(atomAsMacro->name());
		if (selection.size() > 0 && data && data->numargs() - data->optionals() > 0) {
			macroArg = true;
			atomAsMacro->setDisplayMode(MathMacro::DISPLAY_INTERACTIVE_INIT, 1);
		} else

			atomAsMacro->setDisplayMode(MathMacro::DISPLAY_INTERACTIVE_INIT, 0);
	}


	else if (atom.nucleus()->nargs() > 0)
		atom.nucleus()->cell(0).append(selection);

	plainInsert(atom);


	if (macroArg) {
		if (selection.size() > 1 || selection[0]->asScriptInset())
			plainInsert(MathAtom(new InsetMathBrace(selection)));
		else
			insert(selection);
	}

	return true;
}
