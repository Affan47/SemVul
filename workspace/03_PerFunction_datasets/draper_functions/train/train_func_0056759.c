gettoken
(  telRaam* raam
,  i32  mode
)
   {  if (raam->buffered)
      raam->buffered = FALSE
   ;  else
      raam->toktype = getatoken(raam, mode)

   ;  return raam->toktype
;  }
