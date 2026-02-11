gf_smil_timing_init_runtime_info(GF_Node *timed_elt)
{
	GF_SceneGraph *sg;
	SMIL_Timing_RTI *rti;
	SMILTimingAttributesPointers *timingp = NULL;
	u32 tag = gf_node_get_tag(timed_elt);
	SVGAllAttributes all_atts;
	SVGTimedAnimBaseElement *e = (SVGTimedAnimBaseElement *)timed_elt;

	gf_svg_flatten_attributes((SVG_Element *)e, &all_atts);
	e->timingp = gf_malloc(sizeof(SMILTimingAttributesPointers));
	e->timingp->begin		= all_atts.begin;
	e->timingp->clipBegin	= all_atts.clipBegin;
	e->timingp->clipEnd		= all_atts.clipEnd;
	e->timingp->dur			= all_atts.dur;
	e->timingp->end			= all_atts.end;
	e->timingp->fill		= all_atts.smil_fill;
	e->timingp->max			= all_atts.max;
	e->timingp->min			= all_atts.min;
	e->timingp->repeatCount = all_atts.repeatCount;
	e->timingp->repeatDur	= all_atts.repeatDur;
	e->timingp->restart		= all_atts.restart;
	timingp = e->timingp;
	if (!timingp) return;

	if (tag == TAG_SVG_audio || tag == TAG_SVG_video) {


		if (!e->timingp->dur) {
			GF_FieldInfo info;
			gf_node_get_attribute_by_tag((GF_Node *)e, TAG_SVG_ATT_dur, 1, 0, &info);
			e->timingp->dur = (SMIL_Duration *)info.far_ptr;
			e->timingp->dur->type = SMIL_DURATION_MEDIA;
		}
	}

	GF_SAFEALLOC(rti, SMIL_Timing_RTI)
	timingp->runtime = rti;
	rti->timed_elt = timed_elt;
	GF_LOG(GF_LOG_DEBUG, GF_LOG_SMIL, ("[SMIL Timing   ] Time %f - Timed element %s - Initialization\n", gf_node_get_scene_time((GF_Node *)rti->timed_elt), gf_node_get_log_name((GF_Node *)rti->timed_elt)));

	rti->timingp = timingp;
	rti->status = SMIL_STATUS_WAITING_TO_BEGIN;
	rti->evaluate_status = SMIL_TIMING_EVAL_NONE;
	rti->evaluate = gf_smil_timing_null_timed_function;
	rti->scene_time = -1;
	rti->force_reevaluation = 0;
	rti->media_duration = -1;

	GF_SAFEALLOC(rti->current_interval, SMIL_Interval);
	gf_smil_timing_get_first_interval(rti);
	GF_SAFEALLOC(rti->next_interval, SMIL_Interval);
	gf_smil_timing_get_next_interval(rti, 0, rti->next_interval, rti->current_interval->begin);


	sg = timed_elt->sgprivate->scenegraph;
	while (sg->parent_scene) sg = sg->parent_scene;
	gf_smil_timing_add_to_sg(sg, rti);
}
