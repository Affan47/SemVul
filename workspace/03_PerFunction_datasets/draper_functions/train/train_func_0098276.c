op_div(unsigned int a, unsigned int b)
{
			if ((!b)||(b==1)||(a%b)) return -1;
			return a / b;
}
