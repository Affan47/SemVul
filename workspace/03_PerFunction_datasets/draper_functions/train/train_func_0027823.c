expt_pos (const pol2& x, const cl_I& y)
		{

			var pol2 a = x;
			var cl_I b = y;
			while (!oddp(b)) { a = square(a); b = b = b >> 1; }
			var pol2 c = a;
			until (eq(b,1)) {
				b = b >> 1;
				a = square(a);

				if (oddp(b))
					c = mul(a,c);
			}
			return c;
		}
