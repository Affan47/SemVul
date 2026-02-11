write(WriteStream & ws) const
{
	MathEnsurer ensurer(ws);
	if (ws.fragile())
		ws << "\\protect";
	ws << "\\begin{" << name_ << '}';
	if (name_ != "split" && verticalAlignment() != 'c')
		ws << '[' << verticalAlignment() << ']';
	if (name_ == "alignedat")
		ws << '{' << static_cast<unsigned int>((ncols() + 1)/2) << '}';
	InsetMathGrid::write(ws);
	if (ws.fragile())
		ws << "\\protect";
	ws << "\\end{" << name_ << "}\n";
}
