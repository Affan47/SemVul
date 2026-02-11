free_PA_SAM_CHALLENGE_2(PA_SAM_CHALLENGE_2 *data)
{
free_PA_SAM_CHALLENGE_2_BODY(&(data)->sam_body);
while((&(data)->sam_cksum)->len){
free_Checksum(&(&(data)->sam_cksum)->val[(&(data)->sam_cksum)->len-1]);
(&(data)->sam_cksum)->len--;
}
free((&(data)->sam_cksum)->val);
(&(data)->sam_cksum)->val = NULL;
}
