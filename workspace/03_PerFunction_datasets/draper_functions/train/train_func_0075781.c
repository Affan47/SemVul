dumpToTextStream(
                CStream	                    & out ) const
{
	out.printf("\n----------- [vision::TStereoSystemParams] ------------ \n");
	out.printf("Method for 3D Uncert. \t= ");
	switch (uncPropagation)
	{
	case Prop_Linear:
		out.printf("Linear propagation\n");
		break;
	case Prop_UT:
		out.printf("Unscented Transform\n");
		break;
	case Prop_SUT:
		out.printf("Scaled Unscented Transform\n");
		break;
	}

	out.printf("K\t\t\t= [%f\t%f\t%f]\n", K(0,0), K(0,1), K(0,2));
	out.printf(" \t\t\t  [%f\t%f\t%f]\n", K(1,0), K(1,1), K(1,2));
	out.printf(" \t\t\t  [%f\t%f\t%f]\n", K(2,0), K(2,1), K(2,2));

	out.printf("F\t\t\t= [%f\t%f\t%f]\n", F(0,0), F(0,1), F(0,2));
	out.printf(" \t\t\t  [%f\t%f\t%f]\n", F(1,0), F(1,1), F(1,2));
	out.printf(" \t\t\t  [%f\t%f\t%f]\n", F(2,0), F(2,1), F(2,2));

	out.printf("Baseline \t\t= %f\n", baseline);
	out.printf("Pixel std \t\t= %f\n", stdPixel);
	out.printf("Disparity std\t\t= %f\n", stdDisp);
	out.printf("Z maximum\t\t= %f\n", maxZ);
	out.printf("Z minimum\t\t= %f\n", minZ);
	out.printf("Y maximum\t\t= %f\n", maxY);

	out.printf("k Factor [UT]\t\t= %f\n", factor_k);
	out.printf("a Factor [UT]\t\t= %f\n", factor_a);
	out.printf("b Factor [UT]\t\t= %f\n", factor_b);
	out.printf("-------------------------------------------------------- \n");
}
