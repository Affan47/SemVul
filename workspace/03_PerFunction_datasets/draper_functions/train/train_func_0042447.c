sega_generate_vector_list (void)
{
	int deltax, deltay;
	int currentX, currentY;

	int vectorIndex;
	int symbolIndex;

	int rotate, scale;
	int attrib;

	int angle, length;
	int color;

	int draw;

	vector_clear_list();

	symbolIndex = 0;


	vector_add_clip((512-min_x)<<16, (max_y-1536)<<16,
  	              (1536-min_x)<<16, (max_y-512)<<16);


	do {
		draw = vectorram[symbolIndex++];

		if (draw & 1)
		{
			currentX    = vectorram[symbolIndex + 0] | (vectorram[symbolIndex + 1] << 8);
			currentY    = vectorram[symbolIndex + 2] | (vectorram[symbolIndex + 3] << 8);
			vectorIndex = vectorram[symbolIndex + 4] | (vectorram[symbolIndex + 5] << 8);
			rotate      = vectorram[symbolIndex + 6] | (vectorram[symbolIndex + 7] << 8);
			scale       = vectorram[symbolIndex + 8];

			currentX = ((currentX & 0x7ff) - min_x) << 16;
			currentY = (max_y - (currentY & 0x7ff)) << 16;
			vector_add_point ( currentX, currentY, 0, 0);
			vectorIndex &= 0xfff;


			do
			{
				attrib = vectorram[vectorIndex + 0];
				length = vectorram[vectorIndex + 1];
				angle  = vectorram[vectorIndex + 2] | (vectorram[vectorIndex + 3] << 8);

				vectorIndex += 4;


				angle = (angle + rotate) & 0x3ff;
				deltax = sinTable[angle] * scale * length;
				deltay = cosTable[angle] * scale * length;

				currentX += deltax >> 6;
				currentY -= deltay >> 6;

				color = VECTOR_COLOR222((attrib >> 1) & 0x3f);
				if ((attrib & 1) && color)
				{
					if (translucency)
						intensity = 0xa0;
					else
						intensity = 0xff;
				}
				else
					intensity = 0;
				vector_add_point ( currentX, currentY, color, intensity );

			} while (!(attrib & 0x80));
		}

		symbolIndex += 9;
		if (symbolIndex >= vectorram_size)
			break;

	} while (!(draw & 0x80));
}
