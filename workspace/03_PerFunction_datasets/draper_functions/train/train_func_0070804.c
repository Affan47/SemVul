create_mapping_table(
	int nr, int ng, int nb, int ngrey, int grey_bits,
	Bool non_regular_pallet)
{

	Pcsi.grey_bits = 0;


	if (!non_regular_pallet)
	{

		Pcsi.d_nr = nr;
		Pcsi.d_ng = ng;
		Pcsi.d_nb = nb;
		Pcsi.d_ngrey_bits = 2;
		while((1<<Pcsi.d_ngrey_bits) < ngrey)
		{
			Pcsi.d_ngrey_bits++;
		}
		if (1<<Pcsi.d_ngrey_bits != ngrey)
		{
			Pcsi.d_ngrey_bits = 0;
		}
		Pcsi.grey_bits = grey_bits;
	}
	else
	{

		Pcsi.grey_bits = 0;
		if (PColorLimit <= 9)
		{
			Pcsi.d_nr = 3;
			Pcsi.d_ng = 3;
			Pcsi.d_nb = 3;
			Pcsi.d_ngrey_bits = 0;
		}
		else if (PColorLimit <= 64)
		{
			Pcsi.d_nr = 4;
			Pcsi.d_ng = 4;
			Pcsi.d_nb = 4;
			Pcsi.d_ngrey_bits = 0;
		}
		else
		{
			Pcsi.d_nr = 8;
			Pcsi.d_ng = 8;
			Pcsi.d_nb = 8;
			Pcsi.d_ngrey_bits = 0;
		}
		PDitherMappingTable = build_mapping_table(
			Pcsi.d_nr, Pcsi.d_ng, Pcsi.d_nb, non_regular_pallet);
	}


	if (PColorLimit == 2)
	{

		Pcsi.nr = 0;
		Pcsi.ng = 0;
		Pcsi.nb = 0;
		Pcsi.ngrey = 0;
		Pcsi.grey_bits = 1;
	}
	else if (grey_bits > 0)
	{
		Pcsi.nr = 0;
		Pcsi.ng = 0;
		Pcsi.nb = 0;
		Pcsi.ngrey = 0;
		Pcsi.grey_bits = grey_bits;
	}
	else if (non_regular_pallet || (0&&ngrey>0))
	{


		if (PColorLimit <= 9)
		{
			Pcsi.nr = 8;
			Pcsi.ng = 8;
			Pcsi.nb = 8;
			Pcsi.ngrey = 0;
		}
		else
		{
			Pcsi.nr = 16;
			Pcsi.ng = 16;
			Pcsi.nb = 16;
			Pcsi.ngrey = 0;
		}
		PMappingTable = build_mapping_table(
			Pcsi.nr, Pcsi.ng, Pcsi.nb, non_regular_pallet);
	}
	else
	{
		Pcsi.nr = nr;
		Pcsi.ng = ng;
		Pcsi.nb = nb;
		Pcsi.ngrey = ngrey;
		Pcsi.grey_bits = 0;
	}
}
