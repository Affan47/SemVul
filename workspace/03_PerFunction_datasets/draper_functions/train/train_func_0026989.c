main()
{
   char buffer[65536];
   JitterBufferPacket in, out;
   int i;

   JitterBuffer *jb = jitter_buffer_init(10);

   out.data = buffer;


   jitterFill(jb);
   for(i=0;i<100;++i) {
     out.len = 65536;
     jitter_buffer_get(jb, &out, 10, NULL);
     jitter_buffer_tick(jb);
   }
   synthIn(&in, 100, 1);
   jitter_buffer_put(jb, &in);
   out.len = 65536;
   if (jitter_buffer_get(jb, &out, 10, NULL) != JITTER_BUFFER_OK) {
     printf("Failed frozen sender resynchronize\n");
   } else {
     printf("Frozen sender: Jitter %d\n", out.timestamp - 100*10);
   }
   return 0;
}
