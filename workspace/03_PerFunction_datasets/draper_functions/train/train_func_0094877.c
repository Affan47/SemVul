cbf_decode32k_bit_op(char *encoded, char *decoded, size_t size)
{
        unsigned char tmp = '\0';
        unsigned char result = '\0';
        unsigned char mask = 1;

        size_t i = 0,j=0;
        int need= 7, have = -1;

        for(i = 0;i < size; i++)
        {
                result= '\0';
                need = 7;

                while(need > -1)
                {

                        if(have == -1){


                                if(j % 2== 0){
                                        tmp = encoded[j] -offset;
                                        have = 6;
                                } else {
                                        tmp = encoded[j];
                                        have = 7;
                                }
				j++;
                        }
                        result = tmp >>have;
                        result = result & mask;
                        result = result <<need;
                        decoded[i] += result;
                        have--;
 			need--;
                }
        }
	return 1;
}
