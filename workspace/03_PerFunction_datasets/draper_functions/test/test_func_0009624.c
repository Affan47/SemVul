visible_tile_check(struct f3_line_inf *line_t,
								int line,
								UINT32 x_index_fx,UINT32 y_index,
								data32_t *f3_pf_data_n)
{
	data32_t *pf_base;
	int i,trans_all,tile_index,tile_num;
	int alpha_type,alpha_mode;
	int opaque_all;
	int total_elements;

	if(!(alpha_mode=line_t->alpha_mode[line])) return;

	total_elements=Machine->gfx[1]->total_elements;

	tile_index=x_index_fx>>16;
	tile_num=(((line_t->x_zoom[line]*320+(x_index_fx & 0xffff)+0xffff)>>16)+(tile_index%16)+15)/16;
	tile_index/=16;

	if (flipscreen)
	{
		pf_base=f3_pf_data_n+((31-(y_index/16))<<twidth_mask_bit);
		tile_index=(twidth_mask-tile_index)-tile_num+1;
	}
	else pf_base=f3_pf_data_n+((y_index/16)<<twidth_mask_bit);


	trans_all=1;
	opaque_all=1;
	alpha_type=0;
	for(i=0;i<tile_num;i++)
	{
		UINT32 tile=pf_base[(tile_index)&twidth_mask];
		if(tile&0xffff)
		{
			trans_all=0;
			if(opaque_all)
			{
				if(tile_opaque_pf[(tile&0xffff)%total_elements]!=1) opaque_all=0;
			}

			if(alpha_mode==1)
			{
				if(!opaque_all) return;
			}
			else
			{
				if(alpha_type!=3)
				{
					if((tile>>(16+9))&1) alpha_type|=2;
					else				 alpha_type|=1;
				}
				else if(!opaque_all) break;
			}
		}
		else if(opaque_all) opaque_all=0;

		tile_index++;
	}

	if(trans_all)	{line_t->alpha_mode[line]=0;return;}

	if(alpha_mode>1)
	{
		line_t->alpha_mode[line]|=alpha_type<<4;
	}

	if(opaque_all)
		line_t->alpha_mode[line]|=0x80;
}
