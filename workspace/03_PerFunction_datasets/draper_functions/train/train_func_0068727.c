sig_std_logic_resolve(unsigned int val0, unsigned int val1)
{
	switch (val0) {
	case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
	case SIG_STD_LOGIC_X:
		switch (val1) {
		case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
		case SIG_STD_LOGIC_X: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_0: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_1: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_W: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_L: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_H: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_Z: return SIG_STD_LOGIC_X;
		default: assert(0);
		}
	case SIG_STD_LOGIC_0:
		switch (val1) {
		case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
		case SIG_STD_LOGIC_X: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_0: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_1: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_W: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_L: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_H: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_Z: return SIG_STD_LOGIC_0;
		default: assert(0);
		}
	case SIG_STD_LOGIC_1:
		switch (val1) {
		case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
		case SIG_STD_LOGIC_X: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_0: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_1: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_W: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_L: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_H: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_Z: return SIG_STD_LOGIC_1;
		default: assert(0);
		}
	case SIG_STD_LOGIC_W:
		switch (val1) {
		case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
		case SIG_STD_LOGIC_X: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_0: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_1: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_W: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_L: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_H: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_Z: return SIG_STD_LOGIC_W;
		default: assert(0);
		}
	case SIG_STD_LOGIC_L:
		switch (val1) {
		case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
		case SIG_STD_LOGIC_X: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_0: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_1: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_W: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_L: return SIG_STD_LOGIC_L;
		case SIG_STD_LOGIC_H: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_Z: return SIG_STD_LOGIC_L;
		default: assert(0);
		}
	case SIG_STD_LOGIC_H:
		switch (val1) {
		case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
		case SIG_STD_LOGIC_X: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_0: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_1: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_W: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_L: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_H: return SIG_STD_LOGIC_H;
		case SIG_STD_LOGIC_Z: return SIG_STD_LOGIC_H;
		default: assert(0);
		}
	case SIG_STD_LOGIC_Z:
		switch (val1) {
		case SIG_STD_LOGIC_U: return SIG_STD_LOGIC_U;
		case SIG_STD_LOGIC_X: return SIG_STD_LOGIC_X;
		case SIG_STD_LOGIC_0: return SIG_STD_LOGIC_0;
		case SIG_STD_LOGIC_1: return SIG_STD_LOGIC_1;
		case SIG_STD_LOGIC_W: return SIG_STD_LOGIC_W;
		case SIG_STD_LOGIC_L: return SIG_STD_LOGIC_L;
		case SIG_STD_LOGIC_H: return SIG_STD_LOGIC_H;
		case SIG_STD_LOGIC_Z: return SIG_STD_LOGIC_Z;
		default: assert(0);
		}
	default: assert(0);
	}
}
