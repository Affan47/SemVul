beam_collide_asteroid(obj_pair *pair)
{
	beam *b;
	mc_info test_collide;
	int model_num;


	if(pair == NULL){
		return 0;
	}


	Assert(pair->a->instance >= 0);
	Assert(pair->a->type == OBJ_BEAM);
	Assert(Beams[pair->a->instance].objnum == OBJ_INDEX(pair->a));
	b = &Beams[pair->a->instance];


	if((b->warmup_stamp != -1) || (b->warmdown_stamp != -1)){
		return 0;
	}


	if(b->flags & BF_SAFETY){
		return 0;
	}


	if(pair->b == b->objp){
		return 1;
	}


	model_num = beam_get_model(pair->b);
	if(model_num < 0){
		Int3();
		return 1;
	}

#ifndef NDEBUG
	Beam_test_ints++;
	Beam_test_ast++;
#endif


	test_collide.model_instance_num = -1;
	test_collide.model_num = model_num;
	test_collide.submodel_num = -1;
	test_collide.orient = &pair->b->orient;
	test_collide.pos = &pair->b->pos;
	test_collide.p0 = &b->last_start;
	test_collide.p1 = &b->last_shot;
	test_collide.flags = MC_CHECK_MODEL | MC_CHECK_RAY;
	model_collide(&test_collide);


	if(test_collide.num_hits){

		beam_add_collision(b, pair->b, &test_collide);
	}


	if(Use_GLSL < 2)
		beam_add_light(b, OBJ_INDEX(pair->b), 1, NULL);


	pair->next_check_time = timestamp(0);

	return 0;
}
