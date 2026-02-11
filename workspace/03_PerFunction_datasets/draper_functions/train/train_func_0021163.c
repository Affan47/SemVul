play_blast_sound(int blast_type, struct gps *blast_pos)
{
	char fpath[2048];

	if (!Blastmap[blast_type].sound_file)
		return;

	strcpy(fpath, "effects/");
	strcat(fpath, Blastmap[blast_type].sound_file);
	play_sound_at_position(fpath, &Me.pos, blast_pos);
}
