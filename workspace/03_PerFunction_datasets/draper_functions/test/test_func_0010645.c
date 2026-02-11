Blur(int r)
{


    Image temp(*this);

    int sum;


    for (int h=r; h<height-1-r; h++)
        for (int w=r; w<width-1-r; w++)


            for(int i=0; i<3; i++)
            {


                sum = 0;


                for (int j=-r; j<=r; j++)
                    for (int k=-r; k<=r; k++)
                        sum += temp[w+j][h+k][i];

                sum /= pow(1.0+2*r, 2);

                image[w][h][i] = sum;
            }

}
