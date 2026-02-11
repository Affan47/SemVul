init_model_sub(ubyte *p)
{
	Assert(++nest_count < 1000);

	while (w(p) != OP_EOF) {

		switch (w(p)) {

			case OP_DEFPOINTS: {
				int n = w(p+2);
				p += n*sizeof(struct vms_vector) + 4;
				break;
			}

			case OP_DEFP_START: {
				int n = w(p+2);
				p += n*sizeof(struct vms_vector) + 8;
				break;
			}

			case OP_FLATPOLY: {
				int nv = w(p+2);

				Assert(nv > 2);


				p += 30 + ((nv&~1)+1)*2;

				break;
			}

			case OP_TMAPPOLY: {
				int nv = w(p+2);

				Assert(nv > 2);

				if (w(p+28) > highest_texture_num)
					highest_texture_num = w(p+28);

				p += 30 + ((nv&~1)+1)*2 + nv*12;

				break;
			}

			case OP_SORTNORM:

				init_model_sub(p+w(p+28));
				init_model_sub(p+w(p+30));
				p += 32;

				break;


			case OP_RODBM:
				p += 36;
				break;


			case OP_SUBCALL: {
				init_model_sub(p+w(p+16));
				p += 20;
				break;

			}

			case OP_GLOW:
				p += 4;
				break;
			default:
				Error("invalid polygon model\n");
		}
	}
}
