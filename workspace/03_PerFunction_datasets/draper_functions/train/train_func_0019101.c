save( gzFile backup_file )
{

  int8_t tmp_strand = _strand;
  gzwrite( backup_file, &tmp_strand,            sizeof(tmp_strand)            );
  gzwrite( backup_file, &_shine_dal_pos,        sizeof(_shine_dal_pos)        );
  gzwrite( backup_file, &_first_translated_pos, sizeof(_first_translated_pos) );
  gzwrite( backup_file, &_last_translated_pos,  sizeof(_last_translated_pos)  );
  gzwrite( backup_file, &_length,     			    sizeof(_length)               );
  gzwrite( backup_file, &_concentration,     		sizeof(_concentration)        );
  gzwrite( backup_file, &_is_functional,        sizeof(_is_functional)         );
  gzwrite( backup_file, &_mean,  			          sizeof(_mean)                 );
  gzwrite( backup_file, &_width,    			      sizeof(_width)                );
  gzwrite( backup_file, &_height,		     	      sizeof(_height)               );


  int16_t nb_AA = _AA_list->get_nb_elts();
  gzwrite( backup_file, &nb_AA,  sizeof(nb_AA) );

  ae_list_node<ae_codon*>* AA_node = _AA_list->get_first();
  ae_codon* AA;

  for ( int16_t i = 0 ; i < nb_AA ; i++ )
  {
  AA = AA_node->get_obj();

  AA->save( backup_file );

  AA_node = AA_node->get_next();
  }
}
