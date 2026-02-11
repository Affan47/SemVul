get_ip_image_state (unsigned image, unsigned address, unsigned level,
		    unsigned domain, const coding_t *c)


{
   if (level <= c->options.images_level)
   {


      return standard_ip_image_state (address, level, domain, c);
   }
   else
   {


      return c->ip_images_state [domain][image];
   }
}
