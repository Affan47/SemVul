trackFeatures_checkResponses<CFeatureList>(CFeatureList &featureList,const CImage &cur_gray,const float minimum_KLT_response,const unsigned int KLT_response_half_win,const unsigned int max_x, const unsigned int max_y)
			{
				const CFeatureList::iterator itFeatEnd = featureList.end();
				for (CFeatureList::iterator itFeat = featureList.begin(); itFeat!=itFeatEnd ;  ++itFeat)
				{
					CFeature* ft = itFeat->pointer();
					if (ft->track_status!=status_TRACKED)
						continue;

					const unsigned int x = ft->x;
					const unsigned int y = ft->y;
					if (x>KLT_response_half_win && y>KLT_response_half_win && x<max_x && y<max_y)
					{
						ft->response = cur_gray.KLT_response(x,y,KLT_response_half_win);


						if (ft->response<minimum_KLT_response)
						{
							ft->track_status = status_LOST;
						}
					}
					else
					{
						ft->response = 0;
						ft->track_status = status_OOB;
					}
				}
			}
