SkipSection(DXF::LineReader& reader)
{
	for( ;!reader.End() && !reader.Is(0,"ENDSEC"); reader++);
}
